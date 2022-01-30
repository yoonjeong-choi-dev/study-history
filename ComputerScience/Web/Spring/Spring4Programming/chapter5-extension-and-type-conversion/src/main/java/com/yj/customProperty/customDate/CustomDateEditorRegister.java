package com.yj.customProperty.customDate;

import org.springframework.beans.PropertyEditorRegistrar;
import org.springframework.beans.PropertyEditorRegistry;
import org.springframework.beans.propertyeditors.CustomDateEditor;

import java.text.SimpleDateFormat;
import java.util.Date;

public class CustomDateEditorRegister implements PropertyEditorRegistrar {
    private String datePattern;

    public void setDatePattern(String datePattern) {
        this.datePattern = datePattern;
    }

    @Override
    public void registerCustomEditors(PropertyEditorRegistry propertyEditorRegistry) {
        CustomDateEditor editor = new CustomDateEditor(new SimpleDateFormat(datePattern), true);
        propertyEditorRegistry.registerCustomEditor(Date.class, editor);
    }
}
