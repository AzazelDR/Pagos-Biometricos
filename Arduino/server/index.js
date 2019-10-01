const http = require('http');
const express = require('express');
const SocketIO = require('socket.io');

const app = express();
const server = http.createServer(app);
const io = SocketIO.listen(server);

app.use(express.static(__dirname + '/public'));
server.listen(4201, () => console.log('server on port 4201'));

const SerialPort = require('serialport');
const ReadLine = SerialPort.parsers.Readline;

const port = new SerialPort("COM9", {
  baudRate: 57600
});
const parser = port.pipe(new ReadLine({ delimiter: '\r\n' }));

parser.on('open', function () {
  console.log('connection is opened');
});

parser.on('data', function (data) {
  let temp = parseInt(data, 10);
  console.log(temp);
  io.emit('temp', data.toString());
});

parser.on('error', (err) => console.log(err));
port.on('error', (err) => console.log(err));

  