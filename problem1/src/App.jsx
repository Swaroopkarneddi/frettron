import { useState, useEffect } from "react";
import "./App.css";
import FlightPaths from "./FlightPaths";

class Point {
  constructor(x, y) {
    this.x = x;
    this.y = y;
  }

  equals(other) {
    return this.x === other.x && this.y === other.y;
  }
}

function orientation(p, q, r) {
  const val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
  if (val === 0) return 0; // Collinear
  return val > 0 ? 1 : 2; // Clockwise or Counterclockwise
}

function onSegment(p, q, r) {
  return (
    q.x <= Math.max(p.x, r.x) &&
    q.x >= Math.min(p.x, r.x) &&
    q.y <= Math.max(p.y, r.y) &&
    q.y >= Math.min(p.y, r.y)
  );
}

function doIntersect(p1, q1, p2, q2) {
  const o1 = orientation(p1, q1, p2);
  const o2 = orientation(p1, q1, q2);
  const o3 = orientation(p2, q2, p1);
  const o4 = orientation(p2, q2, q1);

  if (o1 !== o2 && o3 !== o4) return true;

  if (o1 === 0 && onSegment(p1, p2, q1)) return true;
  if (o2 === 0 && onSegment(p1, q2, q1)) return true;
  if (o3 === 0 && onSegment(p2, p1, q2)) return true;
  if (o4 === 0 && onSegment(p2, q1, q2)) return true;

  return false;
}

function findIntersection(p1, q1, p2, q2) {
  const a1 = q1.y - p1.y;
  const b1 = p1.x - q1.x;
  const c1 = a1 * p1.x + b1 * p1.y;

  const a2 = q2.y - p2.y;
  const b2 = p2.x - q2.x;
  const c2 = a2 * p2.x + b2 * p2.y;

  const determinant = a1 * b2 - a2 * b1;

  if (determinant === 0) {
    throw new Error("The lines are parallel and do not intersect.");
  }

  const x = (b2 * c1 - b1 * c2) / determinant;
  const y = (a1 * c2 - a2 * c1) / determinant;

  return new Point(x, y);
}

function findAndAdjustIntersections(flights) {
  const setsOfPoints = flights.map((flight) =>
    flight.map((point) => new Point(point[0], point[1]))
  );

  for (let i = 1; i < setsOfPoints.length; ++i) {
    const currentSet = setsOfPoints[i];

    for (let j = 0; j < currentSet.length - 1; ++j) {
      const p1 = currentSet[j];
      const q1 = currentSet[j + 1];

      for (let k = 0; k < i; ++k) {
        const previousSet = setsOfPoints[k];

        for (let l = 0; l < previousSet.length - 1; ++l) {
          const p2 = previousSet[l];
          const q2 = previousSet[l + 1];

          if (
            p1.equals(p2) ||
            p1.equals(q2) ||
            q1.equals(p2) ||
            q1.equals(q2)
          ) {
            continue;
          }

          if (doIntersect(p1, q1, p2, q2)) {
            try {
              const intersection = findIntersection(p1, q1, p2, q2);
              currentSet.splice(j + 1, 0, new Point(q2.x + 1, q2.y));
            } catch (e) {
              // Handle error silently if needed
            }
          }
        }
      }
    }
  }

  return setsOfPoints.map((set) => set.map((pt) => [pt.x, pt.y]));
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

  // const [flights, setFlights] = useState([
  //   [
  //     [1, 1],
  //     [2, 2],
  //     [3, 3],
  //   ],
  //   [
  //     [1, 1],
  //     [3, 2],
  //     [2, 4],
  //   ],
  //   [
  //     [1, 1],
  //     [1, 2],
  //     [2, 3],
  //   ],
  // ]);

  const [updatedFlights, setUpdatedFlights] = useState(flights);

  useEffect(() => {
    const adjustedFlights = findAndAdjustIntersections(flights);
    setUpdatedFlights(adjustedFlights);
  }, [flights]);

  return (
    <>
      <div>hello</div>
      <FlightPaths flights={updatedFlights} />
    </>
  );
}

export default App;
