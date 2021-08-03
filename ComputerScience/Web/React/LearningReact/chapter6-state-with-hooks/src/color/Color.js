import StarRating from "../star_rating/StarRating";
import {FaTrash} from "react-icons/fa";
import { useColors } from "./color-hooks";


const Color = ({
    id, 
    title, 
    color, 
    rating
}) => {
    const {rateColor, removeColor} = useColors();

    return (
        <section>
            <h1>{title}</h1>
            <button onClick={()=>removeColor(id)}>
                <FaTrash/>
            </button>
            <div style={{height:50, background: color }} />
            <StarRating 
                selectedStars={rating} 
                onRate={rating=>rateColor(id, rating)}
            />
        </section>
    )
}

export default Color;