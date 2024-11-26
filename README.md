
# Neural modeling of behavioral timescale plasticity (BTSP)
### C++ codes for modeling of CA3 place cells and their corresponding formation of CA1 place cell based on BTSP.


#### What is BTSP?
*-* Recent form of **synaptic plasticity** observed during the **formation of CA1 place cell.**
*-* It is different from other types of synaptic plasticity such as Hebbian synaptic plasticity, because it requires **only single induction** to change input signals' weights.

*-* *Main biochemical players are...*
- **Eligibility Trace (ET)**: Inputs from upstream CA3 place cells create a transient ET signal
- **Plateau Potential**: Stochastic calcium influx in dendrites induces a plateau potential

*-* When the **ET signal and plateau potential **overlap****, the synaptic **inputs active during this time are selectively potentiated**, enhancing their synaptic weights.

*-* Through this process, a CA1 neuron becomes a place cell, developing place fields aligned with the spatial input patterns from upstream CA3 place cells!

#### Example result
![image](https://github.com/user-attachments/assets/e69c1ec8-3866-4709-a535-3ef13e4e8745)
Above image shows two dendritic plateau potential results in two distinct place fields.


#### References
1. Bittner, Katie C., et al. "Behavioral time scale synaptic plasticity underlies CA1 place fields." Science 357.6355 (2017): 1033-1036.
2. Milstein, Aaron D., et al. "Bidirectional synaptic plasticity rapidly modifies hippocampal representations." Elife 10 (2021): e73046.
3. Fan, Linlin Z., et al. "All-optical physiology resolves a synaptic basis for behavioral timescale plasticity." Cell 186.3 (2023): 543-559.
4. Cone, Ian, and Harel Z. Shouval. "Behavioral time scale plasticity of place fields: mathematical analysis." Frontiers in computational neuroscience 15 (2021): 640235.
5. Grienberger, Christine, and Jeffrey C. Magee. "Entorhinal cortex directs learning-related changes in CA1 representations." Nature 611.7936 (2022): 554-562.
6. Rolotti, Sebi V., et al. "Local feedback inhibition tightly controls rapid formation of hippocampal place fields." Neuron 110.5 (2022): 783-794.
7. Magee, Jeffrey C., and Christine Grienberger. "Synaptic plasticity forms and functions." Annual review of neuroscience 43.1 (2020): 95-117.
8. Wu, Yujie, and Wolfgang Maass. "Memory structure created through behavioral time scale synaptic plasticity." biorxiv (2023): 2023-04.
