import React from "react";
import Ingredient from "./Ingredient";

const IngredientsList = ({ list }) => {
  return (
    <ul className="ingredients">
      {list.map((ingredient, idx) => (
        <Ingredient key={idx} {...ingredient} />
      ))}
    </ul>
  );
};

export default IngredientsList;
