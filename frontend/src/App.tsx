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



const Image: React.FC<{ data: string }> = ({ data }) => (
  // <img width={720} height={480} src={`data:image/jpeg;base64,${data}`} />
  <img src={`data:image/jpeg;base64,${data}`} />
);

let counter = 1;
function App() {
  // const [events, setEvents] = useState<any[]>([]);

    const [imgData, setImgData] = useState("");
    ws.onmessage = (event) => {
      console.log(event);
      // setEvents([event, ...events]);
      const [type, data] = event.data.split(":");
      if (type === "frame") {
        setImgData(data);
      }
    };

    // src={`data:image/png;base64${window.btoa("123")}`}/>
  return (
    <div className="App">
      <header className="App-header">
        <Image data={imgData} />
        {/* <ul>
          {events.map((e, idx) => <li key={idx}>{e.data}</li>)}
        </ul> */}
      </header>
    </div>
  );
}

export default App;
