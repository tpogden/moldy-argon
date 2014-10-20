# Moldy Argon

By Tommy Ogden <<t@ogden.eu>>

Moldy Argon is a molecular dynamics simulator of argon atoms.

## Download

See [Releases] page.

## Use

Compile the app using the makefile. You'll need the GCC installer.

`$ make`

Once compiled, to run the simulator 

`$ moldy_argon`

Parameters you can set for the simulations, with [default value].

* `--num-dims` 
  number of dimensions, i.e. 2 or 3 [2]
* `--num-atoms`
  number of atoms [10]
* `--box-length`
  length of the box containing the atoms, in each dimension. [2]
* `--max-speed`
  max speed ofthe atoms. [2]
* `--t-step` 
  the time step [0.1]
* `--num-t-steps` 
  number of time steps [100]
* `--bc-type`
  boundary condition type ('b': bounce, 't': toroidal, 'n': none) [t]
* `--filename`
  filename to save the simulation ['moldy_argon.json']


e.g. 

```
$ moldy_argon --num-atoms 100 --bc-type b --filename my_file.json
```


## Documentation

This README is the documentation for now. More soon.

## License

See [LICENSE.txt][license].

[license]: https://github.com/tommyogden/moldy-argon/blob/master/LICENSE.txt

[releases]: https://github.com/tommyogden/moldy-argon/releases