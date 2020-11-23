import tensorflow as tf
import tensorflow.contrib.slim as slim
import numpy as np
import matplotlib.pyplot as plt
import random
import scipy.misc
import os
import csv
import itertools



""" Transformation of input grid-state image to a extended flatten vectors"""
def processState(states):
    return np.reshape(states, [84*84*3]);






""" Train the target network which is for target Q in the Bellman equation 
 -tau : Ratio to update target network toward primary network
"""
def updateTarget_network(target_variables, tau):
    total_variables = len(target_variables);
    operation_holder = [];

    for idx, variable in enumerate(target_variables[0:total_variables//2]):
        operation_holder.append(target_variables[idx+total_variables//2].assign(
            (variable.value()*tau) + ((1-tau)*target_variables[idx+total_variables//2].value())
        ));

    return operation_holder;


def updateTarget(op_holders, session):
    for op in op_holders:
        session.run(op);

    num_variables = len(tf.trainable_variables());

    a = tf.trainable_variables()[0].eval(session=session);
    b = tf.trainable_variables()[num_variables//2].eval(session=session);

    if a.all() == b.all():
        print("Target Set Success");
    else:
        print("Target Set Failed");



""" Record performance metrics and episode logs for the Control Center """
def saveToCenter(i, reward_list, ending_step_list, hidden_size, session, main_network, time_per_step):
    with open("./Center/log.csv", "a") as myfile:
        state_display = (np.zeros([1, hidden_size]), np.zeros([1, hidden_size]));
        state_images = [];

        #TODO













""" Make a gif and save the gif of training episode for use in the Control Center """
def make_gif(images, file_name, duration=2, true_image=False, salience=False, salIMGS=None):
    import moviepy.editor as mpy

    def make_frame(t):
        try:
            x = images[int(len(images) / duration*t)];
        except:
            x = images[-1];


        if true_image:
            return x.astype(np.uint8);
        else:
            return ((x+1)/2*255).astype(np.uint8);

    def make_mask(t):
        try:
            x = salIMGS[int(len(salIMGS)/duration*t)];
        except:
            x = salIMGS[-1];

        return x;


    clip = mpy.VideoClip(make_mask, duration=duration);

    if salience is True:
        mask = mpy.VideoClip(make_mask, ismask=True, duration=duration);
        clipB = clip.set_mask(mask);
        clipB = clip.set_opacity(0);
        mask = clip.set_opacity(0.1);
        mask.write_gif(file_name, fps=len(images)/duration, verbose=False);
    else:
        clip.write_gif(file_name, fps=len(images)/duration, verbose=False);























































