import React, { useState } from 'react';
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

const Logs: React.FC<{ data: string[] }> = ({ data }) => (
  <ul>
    {data.map((it, idx) => <li key={idx}>{it}</li>)}
  </ul>
);

let counter = 1;
function App() {
    const [logs, setLogs] = useState<string[]>([]);
    const [imgData, setImgData] = useState<string>("");
    ws.onmessage = (event) => {
      console.log(event);
      const [type, data] = event.data.split("|");
      switch (type) {
        case "frame":
          setImgData(data);
          break;
        case "log":
          setLogs([data, ...logs]);
          break;
      }
    };

  return (
    <div className="App">
      <header className="App-header">
        <Image data={imgData} />
        <Logs data={logs} />
      </header>
    </div>
  );
}

export default App;
