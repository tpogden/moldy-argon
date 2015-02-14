#!/usr/bin/env python

import sys

import numpy as np

import json

import matplotlib.pyplot as plt

import matplotlib.animation as animation

def main():

    json_data = open('moldy_argon.json')

    data = json.load(json_data)

    json_data.close()

    num_t_steps = len(data)

    num_atoms = data[0]['atoms']['num_atoms']
    num_dims = data[0]['atoms']['num_dims']

    pos = np.zeros([num_t_steps, num_atoms, num_dims])

    t_range = np.zeros([num_t_steps])

    for i, t in enumerate(data):
        pos[i] = data[i]['atoms']['pos']
        t_range[i] = data[i]['t']

    box_length = 10.

    # Set up the figure, axis and plot to animate
    fig = plt.figure(figsize=(8.,8.))
    ax = fig.add_subplot(111)
    ax.set_xlim([-box_length/2, box_length/2])
    ax.set_ylim([-box_length/2, box_length/2])

    plot, = ax.plot([], [], 'o')

    t_text = ax.text(0.02, 0.95, '', transform=ax.transAxes)

    # Initialization function: plot the background of each frame
    def init():
        plot.set_data([], [])
        t_text.set_text('')
        return plot, t_text

    # Animation function. This is called sequentially
    def animate(i):
        x = pos[i,:,0]
        y = pos[i,:,1]
        plot.set_data(x, y)
        t_text.set_text('t = %.2f' % t_range[i])
        return plot, t_text

    # call animator.  blit means only re-draw the parts that have changed.
    # anim = animation.FuncAnimation(fig, animate, init_func=init,
    #                                frames=len(t_range),
    #                                interval=200)#, blit=True)

    anim = animation.FuncAnimation(fig, animate, init_func=init, interval=1)

    plt.show()

if __name__ == '__main__':
    status = main()
    sys.exit(status)