var Serialport = require("Serialport");
var $ = require('jquery');
var _ = require('underscore-node');

var port = {};
var is_receiver_ready = false;
var log_txt = ""
var brightness = 0;
var is_new_brightness = false;
var delay_ms = 1;
var port_name = "";

$(document).ready(function() {

    $('.ui.dropdown')
        .dropdown({
            onChange: function(value, text, $selectedItem) {
                port_name = value

                console.log(port_name)
                port = new Serialport(port_name, {
                    baudRate: 115200,
                    parser: Serialport.parsers.readline("\n")
                });

                port.on('open', function() {
                    log_txt = "Serial Port " + port_name + " opened";
                    console.log(log_txt)
                    $('#serial-console').text(log_txt);

                    port.on('data', function(data) {
                        log_txt = "=>" + data
                        console.log(log_txt);
                        $('#serial-console').text(log_txt);
                        is_receiver_ready = true;
                        port.write('0\n');
                    });
                });

                port.on('error', function(err) {
                    console.log('Error: ', err.message);
                    $('#serial-console').text(err.message);
                })

                setInterval(function() {
                    if (is_receiver_ready && is_new_brightness) {
                        $('#serial-console').text(brightness);
                        port.write(brightness + '\n');
                        is_new_brightness = false;
                    }
                }, delay_ms)
            }
        });

    Serialport.list((err, ports) => {
        _.each(ports, function(item) {
            console.log(item.comName);
            let port = '<div class="item" data-value=' + item.comName + '>' + item.comName + '</div>'
            $("#serial-port-list").append(port)
        })
    })

    $('#brightness-slider').range({
        min: 0,
        max: 255,
        start: 0,
        onChange: function(brightness_val) {
            console.log(brightness_val);
            brightness = brightness_val;
            is_new_brightness = true;
        }
    });

    $("#animation-1").click(function() {
        setInterval(function() {
            $('#serial-console').text(brightness);
            port.write(brightness + '\n');
            if (brightness >= 0) brightness--;
            else brightness = 255;
        }, delay_ms)
    })

});
