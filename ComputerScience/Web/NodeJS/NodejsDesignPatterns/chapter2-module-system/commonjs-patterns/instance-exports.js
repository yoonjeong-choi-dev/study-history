class Logger {
  constructor(name) {
    this.name = name;
    this.count = 0;
  }

  log(msg) {
    this.count++;
    console.log(`class : [log-${this.name}] ${msg}(${this.count})`);
  }

};

module.exports = new Logger('DEFAULT');