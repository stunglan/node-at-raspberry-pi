spiDev = "/dev/spidev0.0";
cePin = 24;
irqPin = 25;
var radio = require('nrf').connect(spiDev, cePin, irqPin);
radio.channel(0x1).dataRate('1Mbps').crcBytes(2).autoRetransmit({count:15, delay:4000});
console.log("Started");
radio.begin(function () {
    var rx = radio.openPipe('rx', 0xF0F0F0F0E1),
        tx = radio.openPipe('tx', 0xF0F0F0F0D2);
    // fire 1 to tx
    tx.on('ready', function() {
		console.log("TX Ready");
		tx.write(1); // Send a quick "I'm here" message
	});
    // Fires when our reception pipe recieves data
	rx.on('data', function(d) {
		console.log("Recieved:", d.toString('utf8')); // Decode the data and print 

	});

	// Handler for errors
	tx.on('error', function(e) {
		console.log("Error:", e);
	});
	rx.on('error', function(e) {
		console.log("Error:", e);
	});
        
    //rx.pipe(tx);        // echo back everything
});