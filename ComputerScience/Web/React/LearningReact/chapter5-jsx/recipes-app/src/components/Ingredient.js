import React from "react";

const Ingredient = ({ amount, measurement, name }) => {
  return (
    <li>
      {name} : {amount} ({measurement})
    </li>
  );
};

export default Ingredient;
