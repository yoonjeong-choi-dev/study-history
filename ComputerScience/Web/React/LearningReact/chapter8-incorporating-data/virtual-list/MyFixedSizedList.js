import React from "react";
import {FixedSizeList} from "react-window";


const MyFixedSizedList = ({data=[], renderEmpty}) => {
    if (!data.length) return renderEmpty;

    const renderRow = ({index, style}) => (
        <div sytle={{ ...style, ...{display: "flex"} }} >
            <img
                src={data[index].avatar}
                alt={data[index].name}
                width={50}
            />
            <p>
                {data[index].name} - {data[index].email}
            </p>
        </div>
    )

    return (
        <FixedSizeList 
            height={window.innerHeight}
            widht={window.innerWidth}
            itemCount={data.length}
            itemSize={50}
        >
            {renderRow}
        </FixedSizeList>
    )

}

export default MyFixedSizedList;