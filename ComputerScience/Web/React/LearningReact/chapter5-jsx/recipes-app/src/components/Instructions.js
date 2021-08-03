import React from "react";

const Instructions = ({ title, steps }) => {
  return (
    <section className="instructions">
      <h2>{title}</h2>
      {steps.map((step, idx) => {
        <p key={idx}>
          {" "}
          {idx}. {step}
        </p>;
      })}
      {steps.map((step, idx) => (
        <p key={idx}>
          {" "}
          {idx}. {step}
        </p>
      ))}
    </section>
  );
};

export default Instructions;
