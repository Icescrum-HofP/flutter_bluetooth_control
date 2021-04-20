import 'dart:convert';
import 'dart:typed_data';

import 'package:flutter/cupertino.dart';
import 'package:flutter/services.dart';
import 'package:flutter_bluetooth_serial/flutter_bluetooth_serial.dart';

abstract class Bluetooth {
  Future<List<BluetoothDevice>> getDevices();
  Future<bool> connectTo(String address);
  Stream<BluetoothState> connectionState();
  void write(String message);
  void color(Color color);
  Future<bool> disconnect();
}

class BluetoothService implements Bluetooth {
  final flutterBluetoothSerial = FlutterBluetoothSerial.instance;
  BluetoothConnection bluetoothConnection;

  @override
  Future<List<BluetoothDevice>> getDevices() async {
    List<BluetoothDevice> devices =
        await flutterBluetoothSerial.getBondedDevices();
    try {
      if (devices.isNotEmpty) {
        return devices;
      }
    } on PlatformException {
      print("PlatformException");
    }
  }

  @override
  Future<bool> connectTo(String address) async {
    try {
      bluetoothConnection = await BluetoothConnection.toAddress(address);
      return bluetoothConnection.isConnected;
    } catch (e) {
      return false;
    }
  }

  @override
  Stream<BluetoothState> connectionState() {
    return flutterBluetoothSerial.onStateChanged();
  }

  @override
  void write(String message) {
    if (bluetoothConnection.isConnected) {
      bluetoothConnection.output.add(utf8.encode(message));
    }
  }
@override
  void color(Color color){
    Uint8List values = Uint8List(3);
    values[0] = color.red;
    values[1] = color.green;
    values[2] = color.blue;

    if (bluetoothConnection.isConnected) {
      bluetoothConnection.output.add(values);
    }

  }

  @override
  Future<bool> disconnect() async {
    if (bluetoothConnection.isConnected) {
      await bluetoothConnection.close();
      return false;
    }
    return false;
  }
}
