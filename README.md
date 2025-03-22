# Research - Servo Force Rig

Research project for estimating servo force, contact, and position from internal and external sensors.

## Data Collection

Run *firmware/arduino/servo_sensor_control* on a [SparkFun SAMD21 Mini Breakout](https://www.sparkfun.com/products/13664).

Run *software/python/test_suite.py* on the connected computer to control the servo and log the sensor readings.

## Set Up Machine Learning Docker Image

Make sure you have the latest [Nvidia drivers](https://www.nvidia.com/en-us/drivers/) installed.

Build Docker image to set up the toolchain (requires WSL2 backend for Docker in Windows).

```sh
docker build -t pytorch-gpu .
```

Run the image to serve Jupyter Lab:

Linux/macOS:

```sh
docker run --gpus all -it --rm -v -p 127.0.0.1:8888:8888 -v "$(pwd)":/workspace pytorch-gpu
```

Windows:

```sh
docker run --gpus all -it --rm -p 127.0.0.1:8888:8888 -v "${PWD}:/workspace" pytorch-gpu
```

### Jupyter: Browser Access

Access the Jupyter Lab instance on a browser at [http://localhost:8888/lab](http://localhost:8888/lab).

### Jupyter: VS Code Access

 * In VS Code, install the **Jupyter extension**
 * Open this directory (*research-servo-force-rig*)
 * Open desired .ipynb file
 * Top-right of file, click *Python 3 (ipykernel)* button
   * *Select Another Kernel…*
   * *Existing Jupyter Server…*
   * *Enter the URL of the running Jupyter Server…*
   * Enter http://127.0.0.1:8888/lab
   * *Yes* to connect without a token
   * Give the server a name e.g. "Jupyter Server: pytorch-gpu"
   * Select *Python 3 (ipkernel)* kernel
 * In the future, you can just select “Jupyter Server: pytorch-gpu” from the existing server list

## License

All code, unless otherwise specified, is licensed under the BSD 3-Clause license. See [LICENSE.txt](LICENSE.txt) for more information.
All mechanical drawings, unless otherwise specified, are licensed under the [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/deed.en) license.