var port_name = "/dev/tty.usbserial-A9A15V37";
var SerialPort = require("serialport");
var port = new SerialPort(port_name, {
    baudRate: 115200,
    parser: SerialPort.parsers.readline("\n")
});

port.on('error', function(err) {
    console.log('Error: ', err.message);
})

var is_receiver_ready = false;
port.on('open', function() {
    console.log("Serial Port " + port_name + " opened")
    port.on('data', function(data) {
        console.log("=>" + data);
        is_receiver_ready = true;
        port.write('0\n');
    });
});

var brightness = 20;
var delay_ms = 20;
setInterval(function() {
    if (is_receiver_ready) {
        console.log(brightness)
        port.write(brightness + '\n');
        if (brightness >= 0) brightness -= 0.1;
        else brightness = 20;
    }
}, delay_ms)
