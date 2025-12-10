import { useState, type ChangeEvent, type KeyboardEvent } from "react";

interface ChessSizeInputProps {
  onChangeSize: (n: number, m: number) => void;
}

export default function ChessSizeInput({ onChangeSize }: ChessSizeInputProps) {
  const [rawInput, setRawInput] = useState<string>("");
  const [error, setError] = useState<string>("");
  const [pendingSize, setPendingSize] = useState<{ n: number; m: number } | null>(null);

  function handleChange(event: ChangeEvent<HTMLInputElement>) {
    const value = event.target.value;
    setRawInput(value);

    const regex = /^(\d+)\s*\*\s*(\d+)$/;

    if (regex.test(value)) {
      const match = value.match(regex);
      if (match) {
        const n = Number(match[1]);
        const m = Number(match[2]);
        if (n > 0 && m > 0) {
          setError("");
          setPendingSize({ n, m });
        } else {
          setError("0보다 큰 값을 입력하세요.");
          setPendingSize(null);
        }
      }
    } else {
      setError("형식: n*m 예) 8*8");
      setPendingSize(null);
    }
  }

  function handleKeyDown(event: KeyboardEvent<HTMLInputElement>) {
    if (event.key === "Enter") {
      if (pendingSize) {
        onChangeSize(pendingSize.n, pendingSize.m);
      } else {
        setError("형식: n*m 예) 8*8, 0보다 큰 값만 허용");
      }
    }
  }

  return (
    <>
      <h1>Enter the size of the chessboard (n * m)</h1>
      <input
        type="text"
        value={rawInput}
        onChange={handleChange}
        onKeyDown={handleKeyDown}
        placeholder="예: 8*8"
      />
      <p>값을 입력한 뒤 Enter를 눌러 확정하세요.</p>
      {error && <p style={{ color: "red" }}>{error}</p>}
    </>
  );
}
