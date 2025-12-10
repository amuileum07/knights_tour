import { useState } from "react";
import ChessSizeInput from "./ChessSizeInput";
import ChessBoard from "./ChessBoard";
import "./App.css";

function App() {
  const [n, setN] = useState<number | null>(null);
  const [m, setM] = useState<number | null>(null);

  function handleSizeChange(newN: number, newM: number) {
    if (Number.isNaN(newN) || Number.isNaN(newM) || newN <= 0 || newM <= 0) {
      setN(null);
      setM(null);
      return;
    }
    setN(newN);
    setM(newM);
  }

  return (
    <div className="app">
      {n === null || m === null ? (
        <ChessSizeInput onChangeSize={handleSizeChange} />
      ) : (
        <section className="board-section">
          <ChessBoard rows={n} cols={m} />
        </section>
      )}
    </div>
  );
}

export default App;
