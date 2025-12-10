import { useEffect, useState, type CSSProperties } from "react";

interface ChessBoardProps {
  rows: number;
  cols: number;
}

export default function ChessBoard({ rows, cols }: ChessBoardProps) {
  const [size, setSize] = useState<{ width: number; height: number }>({ width: 360, height: 360 });

  useEffect(() => {
    function updateSize() {
      const vw = window.innerWidth * 0.9;
      const vh = window.innerHeight * 0.8;
      const maxWidth = Math.min(vw, 720);
      const maxHeight = Math.min(vh, 720);

      const widthLimitedByHeight = (maxHeight * cols) / rows;
      const width = Math.min(maxWidth, widthLimitedByHeight);
      const height = (width * rows) / cols;

      setSize({ width, height });
    }

    updateSize();
    window.addEventListener("resize", updateSize);
    return () => window.removeEventListener("resize", updateSize);
  }, [rows, cols]);

  const gridStyle: CSSProperties = {
    gridTemplateColumns: `repeat(${cols}, minmax(32px, 1fr))`,
    gridTemplateRows: `repeat(${rows}, minmax(32px, 1fr))`,
    width: `${size.width}px`,
    height: `${size.height}px`,
  };

  const cells = [];
  for (let r = 0; r < rows; r += 1) {
    for (let c = 0; c < cols; c += 1) {
      const isDark = (r + c) % 2 === 1;
      cells.push(
        <div
          key={`${r}-${c}`}
          className={`cell ${isDark ? "cell-dark" : "cell-light"}`}
          aria-label={`r${r + 1} c${c + 1}`}
        />,
      );
    }
  }

  return (
    <div className="board-wrapper">
      <div className="chessboard" style={gridStyle}>
        {cells}
      </div>
    </div>
  );
}
