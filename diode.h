enum diode_states {
        DIODE_OFF       = 0,
        DIODE_ON        = 1,
};

enum diode_modes {
        DIODE_PHY       = 0,
        DIODE_PWM       = 1, // Pulse-width modulation (ШИМ)
};

enum animation_mode {
        ANI_NORMAL      = 0,
        ANI_REPEAT      = 1,
};

struct animation {
        struct lnode    *head; // Linked list of animation frames
        unsigned int    fps; // Frame rate of animation
        unsigned int    ani_mode; // Animation mode
        unsigned int    repeats; // Number of repeatitions
};

// State of system of diodes
struct dframe {
        struct dstate   *arr;
        unsigned int    len;
};

// State of a single given diode
struct dstate {
        unsigned char   state;
        unsigned char   mode;
};