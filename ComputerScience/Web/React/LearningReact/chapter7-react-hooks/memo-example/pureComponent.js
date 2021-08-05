import React, {memo } from "react";

export const MyComponent = ({name, clicking = f=>f }) => {
    console.log(`rendering "${name}"-component`);
    return <p onClick={()=>clicking(name)}>{name}</p>
};

const PureCompoent = memo(MyComponent, (preProps, nextProps) => preProps.name === nextProps.name);

export default PureCompoent;