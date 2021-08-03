import React, {useState} from "react";
import colorData from "./color-data.json";
import ColorList from "./ColorList";
import AddColorForm from "./AddColorForm";
import {v4} from "uuid";

const ColorListExample = () => {
    const [colors, setColors] = useState(colorData);
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
    }
    return (
        <>
        <AddColorForm onNewColor={addColor}/>
        <ColorList 
            colors={colors} 
            onRemoveColor={id=>{
                const newColors = colors.filter(color=> color.id !== id);
                setColors(newColors);
            }}
            onRateColor={(id, rating) => {
                const newColors = colors.map(color=> color.id === id? {...color, rating} : color);
                setColors(newColors);
            }}
        />
        </>
    );
};

export default ColorListExample;