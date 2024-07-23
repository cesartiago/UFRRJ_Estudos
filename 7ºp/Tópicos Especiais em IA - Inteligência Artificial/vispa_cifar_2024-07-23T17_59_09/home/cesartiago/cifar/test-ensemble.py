#!/usr/bin/env pygpu

import numpy as np
import tensorflow as tf
import cifar10

#
# Fully connected network example for the CIFAR-10 classification task.
# Run this script with 'pygpu %file' in the code editor.
#

# ---------------------------------------------------------
# Load and preprocess CIFAR-10 data
# ---------------------------------------------------------
# X: images, Y: labels
(x_train, y_train), (x_test, y_test) = tf.keras.datasets.cifar10.load_data()

print("images, shape = ", x_train.shape)
print("labels, shape = ", y_train.shape)


def normalize(images):
    mean = np.mean(images, axis=0)[np.newaxis]  # shape = (1, 32, 32, 3)
    sigma = np.std(images, axis=0)[np.newaxis]  # shape = (1, 32, 32, 3)
    images_normalized = (images - mean) / sigma
    return images_normalized


# normalize each pixel and color-channel separately across all images
# take 2000 images for validation from test data
x_train_norm = normalize(x_train)
x_test_norm = normalize(x_test)[:8000]
x_valid_norm = normalize(x_test)[8000:]

# convert labels ("0"-"9") to one-hot encodings, "0" = (1, 0, ... 0) and so on
y_train_onehot = tf.keras.utils.to_categorical(y_train, 10)
y_test_onehot = tf.keras.utils.to_categorical(y_test, 10)[:8000]
y_valid_onehot = tf.keras.utils.to_categorical(y_test, 10)[8000:]

# ----------------------------------------------------------
# Load and evaluate some pre-trained models
# ----------------------------------------------------------

# path to some pre-trained models, you can use your own models here
files = [
    "/net/scratch/deeplearning/CIFAR/models-DCNN/model-1.h5",
    "/net/scratch/deeplearning/CIFAR/models-DCNN/model-2.h5",
    "/net/scratch/deeplearning/CIFAR/models-DCNN/model-3.h5",
    "/net/scratch/deeplearning/CIFAR/models-DCNN/model-4.h5",
    "/net/scratch/deeplearning/CIFAR/models-DCNN/model-5.h5",
]

print("Test performance (loss, accuracy)")
y_ensemble = np.zeros_like(y_test_onehot)

for file in files:
    model = tf.keras.models.load_model(file)
    y_ensemble += model.predict(x_test_norm)
    print(
        "%.3f, %.3f"
        % tuple(model.evaluate(x_test_norm, y_test_onehot, verbose=0, batch_size=128))
    )


# convert back to class labels (0-9)
Y_ensemble_cl = np.argmax(y_ensemble, axis=1)
Y_test_cl = np.argmax(y_test_onehot, axis=1)

# compare prediction and truth
m = Y_ensemble_cl == Y_test_cl
print("Ensemble average: test accuracy = %.3f" % (sum(m) / float(len(m))))

# plot confusion matrix
cifar10.plot_confusion(Y_test_cl, Y_ensemble_cl, fname="confusion_ensemble.png")
