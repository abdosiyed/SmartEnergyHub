#!/usr/bin/env python3
"""
SmartEnergyHub Flask Server
Bridges ESP32 via UART and provides web dashboard
"""

import json
import threading
import serial
import time
from flask import Flask, render_template, jsonify, request
from collections import defaultdict
from datetime import datetime

app = Flask(__name__)

# Configuration
UART_PORT = 'COM3'  # Change to your ESP32 COM port
UART_BAUD = 115200
UART_TIMEOUT = 1

# Global state
latest_room_data = {
    'R1': {'name': 'Living Room', 'power': 0, 'state': 'OFF'},
    'R2': {'name': 'Kitchen', 'power': 0, 'state': 'OFF'},
    'R3': {'name': 'Bedroom 1', 'power': 0, 'state': 'OFF'},
    'R4': {'name': 'Bedroom 2', 'power': 0, 'state': 'OFF'},
    'total': 0
}
data_lock = threading.Lock()
ser = None
rx_buffer = ""

def init_serial():
    """Initialize serial connection to ESP32"""
    global ser
    try:
        ser = serial.Serial(UART_PORT, UART_BAUD, timeout=UART_TIMEOUT)
        print(f"[UART] Connected to {UART_PORT} at {UART_BAUD} baud")
        return True
    except Exception as e:
        print(f"[UART ERROR] Failed to open {UART_PORT}: {e}")
        return False

def uart_reader_thread():
    """Background thread to read from ESP32 UART"""
    global latest_room_data, rx_buffer
    
    while True:
        try:
            if ser and ser.is_open:
                if ser.in_waiting > 0:
                    byte_data = ser.read(ser.in_waiting)
                    rx_buffer += byte_data.decode('utf-8', errors='ignore')
                    
                    # Process complete JSON messages (look for newline)
                    while '\n' in rx_buffer or '\r' in rx_buffer:
                        line, rx_buffer = rx_buffer.split('\n' if '\n' in rx_buffer else '\r', 1)
                        line = line.strip()
                        
                        if line:
                            try:
                                data = json.loads(line)
                                with data_lock:
                                    # Update room data
                                    for room_id in ['R1', 'R2', 'R3', 'R4']:
                                        if room_id in data:
                                            latest_room_data[room_id] = data[room_id]
                                    if 'total' in data:
                                        latest_room_data['total'] = data['total']
                                print(f"[UART RX] {line}")
                            except json.JSONDecodeError:
                                print(f"[UART ERROR] Invalid JSON: {line}")
            else:
                time.sleep(0.1)
        except Exception as e:
            print(f"[UART READER ERROR] {e}")
            time.sleep(1)

def send_command(cmd_dict):
    """Send JSON command to ESP32 via UART"""
    try:
        if ser and ser.is_open:
            cmd_json = json.dumps(cmd_dict)
            ser.write(cmd_json.encode() + b'\n')
            print(f"[UART TX] {cmd_json}")
            return True
    except Exception as e:
        print(f"[UART SEND ERROR] {e}")
    return False

@app.route('/')
def index():
    """Serve main HTML dashboard"""
    return render_template('index.html')

@app.route('/data')
def get_data():
    """Return current room and home data as JSON"""
    with data_lock:
        response = {
            'rooms': {
                'R1': latest_room_data['R1'],
                'R2': latest_room_data['R2'],
                'R3': latest_room_data['R3'],
                'R4': latest_room_data['R4']
            },
            'total': latest_room_data['total']
        }
    return jsonify(response)

@app.route('/toggle', methods=['POST'])
def toggle_room():
    """Toggle room ON/OFF"""
    room = request.args.get('room', 'R1')
    cmd = {'cmd': 'TOGGLE', 'room': room}
    success = send_command(cmd)
    return jsonify({'status': 'success' if success else 'error'})

@app.route('/set_mp', methods=['POST'])
def set_max_power():
    """Set room max power limit"""
    room = request.args.get('room', 'R1')
    value = request.args.get('value', 1000, type=int)
    cmd = {'cmd': 'SET_MP', 'room': room, 'value': value}
    success = send_command(cmd)
    return jsonify({'status': 'success' if success else 'error'})

@app.route('/set_hp', methods=['POST'])
def set_home_power():
    """Set home power budget"""
    value = request.args.get('value', 4000, type=int)
    cmd = {'cmd': 'SET_HP', 'value': value}
    success = send_command(cmd)
    return jsonify({'status': 'success' if success else 'error'})

if __name__ == '__main__':
    # Initialize UART connection
    if init_serial():
        # Start UART reader thread
        reader_thread = threading.Thread(target=uart_reader_thread, daemon=True)
        reader_thread.start()
        
        # Start Flask web server
        print("[SERVER] Starting SmartEnergyHub Flask server on http://localhost:5000")
        app.run(debug=True, host='0.0.0.0', port=5000, use_reloader=False)
    else:
        print("[ERROR] Failed to initialize UART. Exiting.")
