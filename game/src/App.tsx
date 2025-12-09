import { useState } from "react";
import ChessSizeInput from "./ChessSizeInput";
import "./App.css";

function App() {
  const [n, setN] = useState<number | null>(null);
  const [m, setM] = useState<number | null>(null);

  function handleSizeChange(newN: number, newM: number) {
    if (Number.isNaN(newN) || Number.isNaN(newM)) {
      setN(null);
      setM(null);
      return;
    }
    setN(newN);
    setM(newM);
  }

  return (
    <>
      <ChessSizeInput onChangeSize={handleSizeChange} />
      {n !== null && m !== null && (
        <p>
          n = {n}, m = {m}
        </p>
      )}
    </>
  );
}

export default App;
