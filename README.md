# Moldy Argon

By Tommy Ogden <<t@ogden.eu>>

Moldy Argon is a molecular dynamics simulator of argon atoms.

## Download

See [Releases] page.

## Use

Compile the app using the makefile. You'll need the GCC installer.

`$ make`

Once compiled, the simulator can be run with

`$ moldy_argon`

Parameters you can set for the simulations, with [default value].

* `--num-dims` 
  number of dimensions, i.e. 2 or 3 [2]
* `--num-atoms`
  number of atoms [16]
* `--box-length`
  length of the box containing the atoms, in each dimension. [4.0]
* `--max-speed`
  max speed ofthe atoms. [1.0]
* `--t-step` 
  the time step [0.1]
* `--num-t-steps` 
  number of time steps [100]
* `--bc-type`
  boundary condition type ('b': bounce, 't': toroidal, 'n': none) [t]
* `--force-type`
  force type ('l': Lennard-Jones, 'n': none) [l]
* `--cutoff`
   force cutoff distance [0.0]
* `--filename`
  filename to save the simulation ['moldy_argon.json']


e.g. 

```
$ ./moldy_argon --num-atoms 100 --bc-type b --filename my_file.json
```

For 2D simulations, there's a basic visualiser for the dynamics, written in
Python with Numpy and Matplotlib. If you've got those installed, try

```
$ ./moldy_argon
$ python plot/plot_moldy_argon.py
```

to see some atoms moving around.

## Documentation

This README is the documentation for now. More soon.

## License

See [LICENSE.txt][license].

[license]: https://github.com/tommyogden/moldy-argon/blob/master/LICENSE.txt

[releases]: https://github.com/tommyogden/moldy-argon/releases