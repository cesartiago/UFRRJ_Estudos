#!/usr/bin/env -S submit -M 7900 -m 7500 -f python

import numpy as np
import cifar10
import tensorflow as tf
import matplotlib.pyplot as plt
from tabulate import tabulate
layers = tf.keras.layers

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
# Define model
# ----------------------------------------------------------
model = tf.keras.models.Sequential(name="dcnn")


def add_block(nfilters, dropout=False, **kwargs):
    """
    Add basic convolution block:
     - 3x3 Convolution with padding
     - Activation: ReLU
     - either MaxPooling to reduce resolution, or Dropout
     - BatchNormalization
    """
    model.add(layers.Convolution2D(nfilters, kernel_size=(3, 3), padding="same", kernel_initializer="he_normal", **kwargs))
    model.add(layers.BatchNormalization())
    model.add(layers.Activation("relu"))
    if dropout:
        model.add(layers.Dropout(dropout))
    else:
        model.add(layers.MaxPooling2D((2, 2), padding="same"))


# convolution part
add_block(32, dropout=0.3, input_shape=(32, 32, 3))  # --> (32, 32, 32)
add_block(32)  # --> (16, 16,  32)
add_block(64, dropout=0.4)  # --> (16, 16,  64)
add_block(64)  # --> ( 8,  8,  64)
add_block(128, dropout=0.4)  # --> ( 8,  8, 128)
add_block(128, dropout=0.4)  # --> ( 8,  8, 128)
add_block(128)  # --> ( 4,  4, 128)
add_block(256, dropout=0.4)  # --> ( 4,  4, 256)
add_block(256, dropout=0.4)  # --> ( 4,  4, 256)
add_block(256)  # --> ( 2,  2, 256)

# classification part
model.add(layers.Flatten())  # --> (1024)
model.add(layers.Dropout(0.5))
model.add(layers.Dense(256))  # --> (256)
model.add(layers.BatchNormalization())
model.add(layers.Activation("relu"))
model.add(layers.Dropout(0.5))
model.add(layers.Dense(10))  # --> (10)
model.add(layers.Activation("softmax"))

print(model.summary())


# ----------------------------------------------------------
# Training
# ----------------------------------------------------------
model.compile(
    loss="categorical_crossentropy",
    optimizer=tf.keras.optimizers.Adam(lr=1e-3),
    metrics=["accuracy"],
)

batch_size = 32
model.fit(
    x_train_norm,
    y_train_onehot,
    batch_size=batch_size,
    epochs=20,
    verbose=2,
    validation_data=(x_valid_norm, y_valid_onehot),
    callbacks=[tf.keras.callbacks.CSVLogger("history_{}.csv".format(model.name))],
)

model.save("model_{}.h5".format(model.name))  # save trained network

print("Model performance :")
headers = ["", "Loss", "Accuracy"]

table = [
    ["Train", *model.evaluate(x_train_norm, y_train_onehot, verbose=0, batch_size=128)],
    ["Validation", *model.evaluate(x_valid_norm, y_valid_onehot, verbose=0, batch_size=128)],
    ["Test", *model.evaluate(x_test_norm, y_test_onehot, verbose=0, batch_size=128)],
]

print(tabulate(table, headers=headers, tablefmt="orgtbl"))


# ----------------------------------------------------------
# Plots
# ----------------------------------------------------------
# training curves
history = np.genfromtxt("history_{}.csv".format(model.name), delimiter=",", names=True)

fig, ax = plt.subplots(1)
ax.plot(history["epoch"], history["loss"], label="training")
ax.plot(history["epoch"], history["val_loss"], label="validation")
ax.legend()
ax.set(xlabel="epoch", ylabel="loss")
fig.savefig("loss_{}.png".format(model.name))

fig, ax = plt.subplots(1)
ax.plot(history["epoch"], history["accuracy"], label="training")
ax.plot(history["epoch"], history["val_accuracy"], label="validation")
ax.legend()
ax.set(xlabel="epoch", ylabel="accuracy")
fig.savefig("accuracy_{}.png".format(model.name))


# calculate predictions for test set
y_predict = model.predict(x_test_norm, batch_size=128)

# convert back to class labels (0-9)
y_predict_cl = np.argmax(y_predict, axis=1)
y_test_cl = np.argmax(y_test_onehot, axis=1)

# compare prediction and truth
m = y_predict_cl == y_test_cl
i0 = np.arange(8000)[~m]  # misclassified images
i1 = np.arange(8000)[m]  # correctly classified images

# original (unnormalized) test images
x_test = x_test[:8000]

# plot first 10 false classifications
fname = "false_%i_{}.png".format(model.name)
for i in i0[0:10]:
    cifar10.plot_prediction(x_test[i], y_test_onehot[i], y_predict[i], fname=fname % i)

# plot first 10 correct classifications
fname = "correct_%i_{}.png".format(model.name)
for i in i1[0:10]:
    cifar10.plot_prediction(x_test[i], y_test_onehot[i], y_predict[i], fname=fname % i)

# plot confusion matrix
cifar10.plot_confusion(
    y_test_cl, y_predict_cl, fname="confusion_{}.png".format(model.name)
)
