import { useEffect, useMemo, useState, type CSSProperties } from "react";

interface ChessBoardProps {
  rows: number;
  cols: number;
  onReset: () => void;
}

export default function ChessBoard({ rows, cols, onReset }: ChessBoardProps) {
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
      const isVisited = visited.has(`${r}-${c}`);
      cells.push(
        <div
          key={`${r}-${c}`}
          className={`cell ${isDark ? "cell-dark" : "cell-light"} ${canMoveHere ? "cell-move" : ""} ${
            isKnight ? "cell-knight" : ""
          } ${isVisited ? "cell-visited" : ""}`}
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

  function handleUndo() {
    if (path.length === 0) return;
    if (path.length === 1) {
      setPath([]);
      setKnightPos(null);
      return;
    }
    setPath((prev) => {
      const next = prev.slice(0, -1);
      const last = next[next.length - 1];
      setKnightPos(last);
      return next;
    });
  }

  const canUndo = path.length > 0;
  const isComplete = path.length === rows * cols && rows > 0 && cols > 0;

  function handleAnswer() {
    if (!knightPos || isComplete) return;

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

    const visitedSet = new Set<string>();
    path.forEach((p) => visitedSet.add(`${p.row}-${p.col}`));

    const total = rows * cols;

    function degree(r: number, c: number, seen: Set<string>) {
      let count = 0;
      for (const [dr, dc] of moves) {
        const nr = r + dr;
        const nc = c + dc;
        if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && !seen.has(`${nr}-${nc}`)) {
          count += 1;
        }
      }
      return count;
    }

    const additional: Array<{ row: number; col: number }> = [];
    let current = { ...knightPos };

    while (visitedSet.size < total) {
      const candidates: Array<{ row: number; col: number; deg: number }> = [];
      for (const [dr, dc] of moves) {
        const nr = current.row + dr;
        const nc = current.col + dc;
        const key = `${nr}-${nc}`;
        if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && !visitedSet.has(key)) {
          candidates.push({ row: nr, col: nc, deg: degree(nr, nc, visitedSet) });
        }
      }

      if (candidates.length === 0) break;

      candidates.sort((a, b) => a.deg - b.deg);
      const minDeg = candidates[0].deg;
      const smallest = candidates.filter((c) => c.deg === minDeg);
      const choice = smallest[Math.floor(Math.random() * smallest.length)];

      visitedSet.add(`${choice.row}-${choice.col}`);
      additional.push({ row: choice.row, col: choice.col });
      current = { row: choice.row, col: choice.col };
    }

    if (additional.length > 0) {
      setPath((prev) => [...prev, ...additional]);
      setKnightPos(additional[additional.length - 1]);
    }
  }

  return (
    <>
      <div className="board-layout">
        <div className="board-wrapper">
          <div className="chessboard" style={gridStyle}>
            <svg className="path-lines" viewBox={`0 0 ${size.width} ${size.height}`} aria-hidden="true">
              {lines}
            </svg>
            {cells}
          </div>
        </div>
        <div className="board-controls">
          <button
            type="button"
            className="triangle-btn"
            onClick={handleUndo}
            disabled={!canUndo}
            aria-label="한 수 물리기"
          >
            <svg className="triangle-icon" viewBox="0 0 48 48" aria-hidden="true">
              <path d="M10 4 L10 44 L42 24 Z" fill="#ffffff" stroke="#000000" strokeWidth="3" />
            </svg>
        </button>
        <button type="button" className="reset-btn" onClick={onReset} aria-label="초기화">
          <span className="reset-icon" aria-hidden="true" />
        </button>
        <button type="button" className="answer-btn" onClick={handleAnswer} disabled={!knightPos || isComplete}>
          Answer
        </button>
      </div>
    </div>
      {isComplete && (
        <div className="success-panel">
          <h1>success!</h1>
          <button type="button" className="again-btn" onClick={onReset}>
            Again?
          </button>
        </div>
      )}
    </>
  );
}
