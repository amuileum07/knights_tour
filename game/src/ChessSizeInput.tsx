import { useState } from "react";

interface ChessSizeInputProps {
  onChangeSize: (n: number, m: number) => void;
}

export default function ChessSizeInput({ onChangeSize }: ChessSizeInputProps) {
  const [rawInput, setRawInput] = useState<string>("");
  const [error, setError] = useState<string>("");

  function handleChange(event: React.ChangeEvent<HTMLInputElement>) {
    const value = event.target.value;
    setRawInput(value);

    const regex = /^(\d+)\s*\*\s*(\d+)$/; 

    if (regex.test(value)) {
      const match = value.match(regex);
      if (match) {
        const n = Number(match[1]);
        const m = Number(match[2]);
        setError("");
        onChangeSize(n, m); 
      }
    } else {
      setError("형식: n*m 예) 8*8");
      onChangeSize(NaN, NaN); 
    }
  }

  return (
    <>
      <h1>Enter the size of the chessboard (n * m)</h1>
      <input
        type="text"
        value={rawInput}
        onChange={handleChange}
        placeholder="예: 8*8"
      />
      {error && <p style={{ color: "red" }}>{error}</p>}
    </>
  );
}