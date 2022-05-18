const hostname = window && window.location && window.location.hostname;

let todoServerHost;
if(hostname === 'localhost') {
  todoServerHost = 'http://localhost:2205';
}

export const API_BASE = `${todoServerHost}`;