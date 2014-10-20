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

    num_atoms = data[0]['atoms']['num_atoms']
    num_dims = data[0]['atoms']['num_dims']

    num_t_steps = len(data)

    pos = np.zeros([num_t_steps, num_atoms, num_dims])
    t_range = np.zeros([num_t_steps])

    for i, t in enumerate(data):
        pos[i] = data[i]['atoms']['pos']
        t_range[i] = data[i]['t']

    # Set up the figure, axis and plot to animate
    fig = plt.figure(figsize=(8.,8.))
    ax = fig.add_subplot(111)
    ax.set_xlim([-5., 5.])
    ax.set_ylim([-5., 5.])

    x = pos[0,:,0]
    y = pos[0,:,1]

    scat = ax.scatter(x, y)

    t_text = ax.text(0.02, 0.95, '', transform=ax.transAxes)

    xy = [x,y]

    # Initialization function: plot the background of each frame
    def init():
        x = pos[0,:,0]
        y = pos[0,:,1]
        scat.set_offsets([x, y])
        # scat = ax.scatter(x, y, animated=True)
        # scat = ax.scatter(x, y, c='b', s=10) # , animated=True)
        t_text.set_text('')
        return scat, t_text

    # Animation function. This is called sequentially
    def animate(i):
        x = pos[i,:,0]
        y = pos[i,:,1]
        scat.set_offsets([x, y]) #, animated=True)
        # scat.set_offsets(x, y, c='b', s=10) #, animated=True)
        # scat = ax.scatter(x, y, animated=True)
        t_text.set_text('t = %.2f' % t_range[i])
        fig.canvas.draw()
        return scat, t_text

    # # call animator.  blit means only re-draw the parts that have changed.
    # # anim = animation.FuncAnimation(fig, animate, init_func=init,
    # #                                frames=len(t_range),
    # #                                interval=200)#, blit=True)

    anim = animation.FuncAnimation(fig, animate, init_func=init, interval=50, blit=False)

    # anim = animation.FuncAnimation(fig, animate, init_func=init, frames=num_t_steps,
        # interval=50, blit=False)

    plt.show()

if __name__ == '__main__':
    status = main()
    sys.exit(status)