const { EventEmitter } = require('events');

class Ticker extends EventEmitter {
  constructor(tickTime=50) {
    super();
    this.tickTime = tickTime;
    this.tickNumber = 0;
    this.duration = 0;
  }

  tick(time, cb) {
    this.tickNumber = 0;
    this.duration = time;

    this.__recursive(cb);

    return this;
  }

  __recursive(cb) {
    if (this.duration <= 0) {
      return cb(null, this.tickNumber);
    }
    setTimeout(() => {
      this.emit('tick', this.tickNumber);
      this.tickNumber++;
      this.duration -= this.tickTime;

      this.__recursive(cb);
    }, this.tickTime);
  }
}

const ticker = new Ticker(50);

ticker.tick(200, (err, data) => console.log(`The number of ticks : ${data}`))
  .on('tick', (number) => console.log(`${number} : TICK!`));