import React, {createContext, useState, useContext} from "react";
import colorData from "./color-data.json";
import {v4} from "uuid";

const ColorContext = createContext();
export const useColors = () => useContext(ColorContext);

const ColorProvider = ({children}) => {
    const [colors, setColors] = useState(colorData);

    // 컨텍스트 변경을 위해 제공하는 함수들
    const addColor = (title, color) => {
        const newColors = [
            ...colors,
            {
                id: v4(),
                rating: 0,
                title,
                color,
            }
        ];
        setColors(newColors);
    };

    const rateColor = (id, rating) => {
        const newColors = colors.map(color=> color.id === id? {...color, rating} : color);
        setColors(newColors);
    };

    const removeColor = (id) => {
        const newColors = colors.filter(color=> color.id !== id);
        setColors(newColors);
    };

    return (
        <ColorContext.Provider value={{colors, addColor, rateColor, removeColor}}>
            {children}
        </ColorContext.Provider>
    );
}

export default ColorProvider;
