import { useEffect, useMemo, useState, type CSSProperties } from "react";

interface ChessBoardProps {
  rows: number;
  cols: number;
}

export default function ChessBoard({ rows, cols }: ChessBoardProps) {
  const [size, setSize] = useState<{ width: number; height: number }>({ width: 360, height: 360 });
  const [knightPos, setKnightPos] = useState<{ row: number; col: number } | null>(null);
  const [path, setPath] = useState<Array<{ row: number; col: number }>>([]);

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

  const visited = useMemo(() => {
    const set = new Set<string>();
    path.forEach((p) => set.add(`${p.row}-${p.col}`));
    return set;
  }, [path]);

  const reachable = useMemo(() => {
    if (!knightPos) return new Set<string>();
    const moves = [
      [2, 1],
      [1, 2],
      [-1, 2],
      [-2, 1],
      [-2, -1],
      [-1, -2],
      [1, -2],
      [2, -1],
    ];
    const targets = new Set<string>();
    for (const [dr, dc] of moves) {
      const nr = knightPos.row + dr;
      const nc = knightPos.col + dc;
      if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && !visited.has(`${nr}-${nc}`)) {
        targets.add(`${nr}-${nc}`);
      }
    }
    return targets;
  }, [knightPos, rows, cols, visited]);

  const gridStyle: CSSProperties = {
    gridTemplateColumns: `repeat(${cols}, minmax(32px, 1fr))`,
    gridTemplateRows: `repeat(${rows}, minmax(32px, 1fr))`,
    width: `${size.width}px`,
    height: `${size.height}px`,
  };

  function handleSelect(row: number, col: number) {
    const key = `${row}-${col}`;
    // First placement
    if (!knightPos) {
      setKnightPos({ row, col });
      setPath([{ row, col }]);
      return;
    }
    // Only allow legal unvisited moves
    if (reachable.has(key)) {
      setKnightPos({ row, col });
      setPath((prev) => [...prev, { row, col }]);
    }
  }

  const cellWidth = size.width / cols;
  const cellHeight = size.height / rows;
  const lines = path.slice(1).map((pos, idx) => {
    const prev = path[idx];
    const x1 = (prev.col + 0.5) * cellWidth;
    const y1 = (prev.row + 0.5) * cellHeight;
    const x2 = (pos.col + 0.5) * cellWidth;
    const y2 = (pos.row + 0.5) * cellHeight;
    return <line key={`line-${idx}`} x1={x1} y1={y1} x2={x2} y2={y2} />;
  });

  const cells = [];
  for (let r = 0; r < rows; r += 1) {
    for (let c = 0; c < cols; c += 1) {
      const isDark = (r + c) % 2 === 1;
      const isKnight = knightPos?.row === r && knightPos?.col === c;
      const canMoveHere = reachable.has(`${r}-${c}`);
      cells.push(
        <div
          key={`${r}-${c}`}
          className={`cell ${isDark ? "cell-dark" : "cell-light"} ${canMoveHere ? "cell-move" : ""} ${
            isKnight ? "cell-knight" : ""
          }`}
          aria-label={`r${r + 1} c${c + 1}`}
          onClick={() => handleSelect(r, c)}
          role="button"
          tabIndex={0}
          onKeyDown={(event) => {
            if (event.key === "Enter" || event.key === " ") {
              event.preventDefault();
              handleSelect(r, c);
            }
          }}
        >
          {isKnight && <img src="/knight.png" alt="Knight" className="knight-icon" />}
        </div>,
      );
    }
  }

  return (
    <div className="board-wrapper">
      <div className="chessboard" style={gridStyle}>
        <svg className="path-lines" viewBox={`0 0 ${size.width} ${size.height}`} aria-hidden="true">
          {lines}
        </svg>
        {cells}
      </div>
    </div>
  );
}
