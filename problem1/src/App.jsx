import { useState, useEffect } from "react";
import reactLogo from "./assets/react.svg";
import viteLogo from "/vite.svg";
import "./App.css";
import FlightPaths from "./FlightPaths";

class Point {
  constructor(x, y) {
    this.x = x;
    this.y = y;
  }

  displayPoint() {
    return `(${this.x}, ${this.y})`;
  }
}

function lineSegmentIntersection(A, B, C, D) {
  const a1 = B.y - A.y;
  const b1 = A.x - B.x;
  const c1 = a1 * A.x + b1 * A.y;

  const a2 = D.y - C.y;
  const b2 = C.x - D.x;
  const c2 = a2 * C.x + b2 * C.y;

  const determinant = a1 * b2 - a2 * b1;

  if (determinant === 0) {
    return null;
  } else {
    const x = Math.round((b2 * c1 - b1 * c2) / determinant);
    const y = Math.round((a1 * c2 - a2 * c1) / determinant);
    const intersection = new Point(x, y);

    if (
      isPointOnSegment(A, B, intersection) &&
      isPointOnSegment(C, D, intersection)
    ) {
      return intersection;
    } else {
      return null;
    }
  }
}

function isPointOnSegment(A, B, P) {
  const minX = Math.min(A.x, B.x);
  const maxX = Math.max(A.x, B.x);
  const minY = Math.min(A.y, B.y);
  const maxY = Math.max(A.y, B.y);

  return P.x >= minX && P.x <= maxX && P.y >= minY && P.y <= maxY;
}

function suggestNewPoint(C, D, intersection) {
  return new Point(
    intersection.x + (D.x - C.x > 0 ? 1 : -1),
    intersection.y + (D.y - C.y > 0 ? 1 : -1)
  );
}

function findAndAdjustIntersections(flights) {
  function checkIntersections(path1, path2) {
    for (let i = 0; i < path1.length - 1; i++) {
      for (let j = 0; j < path2.length - 1; j++) {
        const A = new Point(path1[i][0], path1[i][1]);
        const B = new Point(path1[i + 1][0], path1[i + 1][1]);
        const C = new Point(path2[j][0], path2[j][1]);
        const D = new Point(path2[j + 1][0], path2[j + 1][1]);

        if (
          (A.x === 1 && A.y === 1) ||
          (B.x === 1 && B.y === 1) ||
          (C.x === 1 && C.y === 1) ||
          (D.x === 1 && D.y === 1)
        ) {
          continue;
        }

        const intersection = lineSegmentIntersection(A, B, C, D);

        if (intersection) {
          const newPoint = suggestNewPoint(C, D, intersection);

          path2.splice(j + 1, 1, [newPoint.x, newPoint.y]);

          return flights.map((path, index) =>
            index === flights.indexOf(path2) ? path2 : path
          );
        }
      }
    }
    return flights;
  }

  const updatedFlights = [...flights];

  for (let i = 0; i < updatedFlights.length; i++) {
    for (let j = i + 1; j < updatedFlights.length; j++) {
      const adjustedPaths = checkIntersections(
        updatedFlights[i],
        updatedFlights[j]
      );
      if (adjustedPaths !== updatedFlights) {
        return { updatedPaths: adjustedPaths, intersections: [] };
      }
    }
  }

  return { updatedPaths: updatedFlights, intersections: [] };
}

function App() {
  const [flights, setFlights] = useState([
    [
      [1, 1],
      [2, 2],
      [3, 3],
    ],
    [
      [1, 1],
      [2, 4],
      [3, 2],
    ],
    [
      [1, 1],
      [4, 2],
      [3, 4],
    ],
  ]);

  const [updatedFlights, setUpdatedFlights] = useState(flights);
  const [intersections, setIntersections] = useState([]);

  useEffect(() => {
    const { updatedPaths, intersections } = findAndAdjustIntersections(flights);
    setUpdatedFlights(updatedPaths);
    setIntersections(intersections);
  }, [flights]);

  return (
    <>
      <div>hello</div>
      <FlightPaths flights={updatedFlights} intersections={intersections} />
    </>
  );
}

export default App;
