package com.yj.di;

import lombok.Getter;
import lombok.ToString;
import org.springframework.stereotype.Component;

@Component
@ToString
@Getter
public class Hotel {

    private Chef chef;

    public Hotel(Chef chef) {
        this.chef = chef;
    }
}
