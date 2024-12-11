# Machine learning development image (Jupyter Notebook server)

# Settings
ARG BASE_IMAGE=nvidia/cuda:12.6.3-cudnn-devel-ubuntu24.04
ARG PYTORCH_VERSION=2.4.1
ARG TORCHAUDIO_VERSION=2.4.1
ARG TORCHVISION_VERSION=0.19.1
ARG KERAS_VERSION=3.7.0
ARG KERAS_BACKEND=torch
ARG VIRTUAL_ENV=/opt/venv

#-------------------------------------------------------------------------------
# Base Image and Dependencies

# Base image
FROM ${BASE_IMAGE}

# Redeclare arguments after FROM
ARG PYTORCH_VERSION
ARG TORCHAUDIO_VERSION
ARG TORCHVISION_VERSION
ARG KERAS_VERSION
ARG KERAS_BACKEND
ARG VIRTUAL_ENV

# Set environment variables
ENV DEBIAN_FRONTEND=noninteractive

# Install system dependencies
RUN apt-get update && \
    apt-get install -y \
        git \
        python3-pip \
        python3-dev \
        python3-opencv \
        python3-venv \
        libglib2.0-0

# Set up a Python virtual environment
ENV VIRTUAL_ENV=${VIRTUAL_ENV}
RUN python3 -m venv ${VIRTUAL_ENV}
ENV PATH="${VIRTUAL_ENV}/bin:$PATH"

# Upgrade pip
RUN python3 -m pip install --upgrade pip

# Install Python dependencies
RUN python3 -m pip install --upgrade pip && \
    python3 -m pip install \
        torch==${PYTORCH_VERSION} \
        torchaudio==${TORCHAUDIO_VERSION} \
        torchvision==${TORCHVISION_VERSION} \
        keras==${KERAS_VERSION} \
        jupyterlab \
        matplotlib \
        pandas \
        scikit-learn

# Activate the Python environment for shell sessions
RUN echo "source ${VIRTUAL_ENV}/bin/activate" >> /root/.bashrc 

# Set the default Keras backend
ENV KERAS_BACKEND=${KERAS_BACKEND}

# Set jupyter-lab as the default entrypoint
ENTRYPOINT ["jupyter-lab", \
    "--allow-root", \
    "--ip=0.0.0.0", \
    "--no-browser", \
    "--notebook-dir=/workspace", \
    "--NotebookApp.token=" \
]
