const os = require("os");

console.log("============= OS Information =============");
console.log("os.arch() : ", os.arch());
console.log("os.platform() : ", os.platform());
console.log("os.type() : ", os.type());
console.log("os.uptime() : ", os.uptime());
console.log("os.hosname() : ", os.hostname());
console.log("os.release() : ", os.release());

console.log("============= Dir Information =============");
console.log("os.homedir() : ", os.homedir());
console.log("os.tmpdir() : ", os.tmpdir());

console.log("============= CPU Information =============");
console.log("os.cpus() : ", os.cpus());
console.log("os.cpus().length : ", os.cpus().length);

console.log("============= Memory Information =============");
console.log("os.freemem() : ", os.freemem());
console.log("os.totalmem() : ", os.totalmem());