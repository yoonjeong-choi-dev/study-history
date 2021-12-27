class Logger {
  constructor(name) {
    this.name = name;
  }

  log(msg) {
    console.log(`class : [log-${this.name}] ${msg}`);
  }

  info(msg) {
    console.log(`class : [info-${this.name}] ${msg}`);
  }
};

module.exports = Logger;