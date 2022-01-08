import React, {useState} from 'react';
import SimpleAdd from './SimpleAdd';

const Example = () => {
  const [formData, setFormData] = useState({'title1': '', 'title2': ''});

  const onChangeInput = (e) => {
    setFormData({
      ...formData,
      [e.target.name]: e.target.value
    });
  }

  return (
    <div>
      <div>
        <input name='title1' onChange={onChangeInput} />
        <SimpleAdd title={formData.title1} />
      </div>
      <div>
        <input name='title2' onChange={onChangeInput} />
        <SimpleAdd title={formData.title2} />
      </div>
    </div>
  );
}

export default Example;