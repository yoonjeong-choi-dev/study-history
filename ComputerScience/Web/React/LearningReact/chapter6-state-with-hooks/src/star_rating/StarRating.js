import React from "react";
import Star from "./Star";
import { createArray } from "../utils/lib";


const StarRating = ({
    style = {},
    totalStars = 5,
    selectedStars = 0,
    onRate = f=>f
}) => {
    return (
        <div style={{padding: "5px", ...style}}>
            {createArray(totalStars).map( (n ,i) => 
                <Star 
                    key={i}
                    selected={selectedStars > i}
                    onSelect={()=>onRate(i+1)}
                />
            )}
            <p>
                {selectedStars} of {totalStars} Stars
            </p>
        </div>
    );
};

export default StarRating;