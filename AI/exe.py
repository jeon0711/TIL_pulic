import numpy as np
import tensorflow as tf
w=tf.Variable(0,dtype=np.float32)
optimizer=tf.keras.optimizers.Adam(0.1)#0.1==learning rate

def train_step():
    with tf.GradientTape() as tape:
        cost=w**2-10*w+25
    trainable_variable=[w]
    gradis=tape.gradient(cost,trainable_variable)
    optimizer.apply_gradients(zip(gradis,trainable_variable))
train_step()
