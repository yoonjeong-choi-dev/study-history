import React from "react";
import Recipe from "./Recipe";

const Menu = ({ title, recipes }) => {
  return (
    <article>
      <header>
        <h1>{title}</h1>
      </header>
      <div className="recipes">
        {recipes.map((recipe, idx) => (
          <Recipe key={idx} {...recipe} />
        ))}
      </div>
    </article>
  );
};

export default Menu;