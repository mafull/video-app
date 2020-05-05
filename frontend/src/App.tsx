import React, { useState } from 'react';
import logo from './logo.svg';
import './App.css';

const ws = new WebSocket('ws://localhost:8080');

    ws.onopen = () => {
      setInterval(() => ws.send(JSON.stringify({ hello: "me", counter: counter++ })), 5000);
    };
    ws.onclose = () => {
      ws.close();
    };



let counter = 1;
function App() {
  const [events, setEvents] = useState<any[]>([]);

    ws.onmessage = (event) => {
      console.log(event);
      setEvents([event, ...events]);
    };


  return (
    <div className="App">
      <header className="App-header">
        <ul>
          {events.map((e, idx) => <li key={idx}>{e.data}</li>)}
        </ul>
      </header>
    </div>
  );
}

export default App;
