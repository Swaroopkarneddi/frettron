import React, { useEffect, useRef } from "react";
import * as d3 from "d3";

const FlightPaths = ({ flights }) => {
  const svgRef = useRef();

  useEffect(() => {
    const svg = d3.select(svgRef.current);
    svg.selectAll("*").remove(); // Clear previous drawings

    // Define dimensions and scales
    const width = 500;
    const height = 500;
    const margin = { top: 20, right: 30, bottom: 30, left: 40 };
    const xScale = d3
      .scaleLinear()
      .domain([0, 5])
      .range([margin.left, width - margin.right]);
    const yScale = d3
      .scaleLinear()
      .domain([0, 5])
      .range([height - margin.bottom, margin.top]);

    // Create an axis
    const xAxis = d3.axisBottom(xScale);
    const yAxis = d3.axisLeft(yScale);

    svg
      .append("g")
      .attr("transform", `translate(0, ${height - margin.bottom})`)
      .call(xAxis);

    svg
      .append("g")
      .attr("transform", `translate(${margin.left}, 0)`)
      .call(yAxis);

    // Draw grid lines
    svg
      .append("g")
      .attr("class", "grid")
      .attr("transform", `translate(0, ${height - margin.bottom})`)
      .call(
        d3
          .axisBottom(xScale)
          .tickSize(-height + margin.top + margin.bottom)
          .tickFormat("")
      )
      .selectAll(".tick line")
      .attr("stroke", "#e0e0e0");

    svg
      .append("g")
      .attr("class", "grid")
      .attr("transform", `translate(${margin.left}, 0)`)
      .call(
        d3
          .axisLeft(yScale)
          .tickSize(-width + margin.left + margin.right)
          .tickFormat("")
      )
      .selectAll(".tick line")
      .attr("stroke", "#e0e0e0");

    // Define a line generator
    const lineGenerator = d3
      .line()
      .x((d) => xScale(d[0]))
      .y((d) => yScale(d[1]));

    // Define colors for each flight path
    const colors = d3.schemeCategory10;

    // Draw each flight path with different colors
    flights.forEach((flight, index) => {
      // Draw the path
      svg
        .append("path")
        .datum(flight)
        .attr("fill", "none")
        .attr("stroke", colors[index % colors.length])
        .attr("stroke-width", 2)
        .attr("d", lineGenerator);

      // Draw circles for each point (except the start point)
      flight.slice(1).forEach((point) => {
        svg
          .append("circle")
          .attr("cx", xScale(point[0]))
          .attr("cy", yScale(point[1]))
          .attr("r", 5)
          .attr("fill", colors[index % colors.length]);
      });
    });

    // Draw the starting point
    const startPoint = flights[0][0];
    svg
      .append("circle")
      .attr("cx", xScale(startPoint[0]))
      .attr("cy", yScale(startPoint[1]))
      .attr("r", 5)
      .attr("fill", "red")
      .attr("stroke", "black")
      .attr("stroke-width", 2);
  }, [flights]);

  return <svg ref={svgRef} width={500} height={500} />;
};

export default FlightPaths;
