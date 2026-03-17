#include "gdexample.h"
#include "godot_cpp/classes/global_constants.hpp"
#include "godot_cpp/core/object.hpp"
#include "godot_cpp/core/property_info.hpp"
#include "godot_cpp/variant/variant.hpp"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

/*
 * `Signals`
 * Having your extension react to a signal given out by another object requires you to call `connect` on that object
 * `some_other_node->connect( "the_signal", Callable( this, "my_method" ) );`
 * 
 * `Callable` holds information about an object on which a method can be called.
 * In the previous example: `this` with the method `my_method` of the object
 * Then the `connect` method will add this to the observers of `the_signal`
 * Whenever `the_signal` is now emitted, Godot knows which method of which object it needs to call
 * 
 * NOTE: you can only call `my_method` if it is registered in `_bind_methods`
 */

void GDExample::_bind_methods() {
    ClassDB::bind_method( D_METHOD( "get_speed" ), &GDExample::get_speed );
    ClassDB::bind_method( D_METHOD( "set_speed", "p_speed" ), &GDExample::set_speed );

    ADD_PROPERTY(
        PropertyInfo(
            Variant::FLOAT,
            "speed",
            PROPERTY_HINT_RANGE,
            "0,20,0.01"
        ),
        "set_speed",
        "get_speed"
    );
    /*
     * The `ADD_SIGNAL` macro can be a single call with a `MethodInfo` argument
     * `MethodInfo`'s first param will be the singal's name
     * Its remaining params are `PropertyInfo`
     * `PropertyInfo` parameters are defind with the data type of the parameter,
     *      then the name that the param will have by default
     */
    ADD_SIGNAL(
        MethodInfo(
            "position_changed",
            PropertyInfo(
                Variant::OBJECT,
                "node"
            ),
            PropertyInfo(
                Variant::VECTOR2,
                "new_pos"
            )
        )
    );
}

GDExample::GDExample() {
    time_passed = 0.0;
    time_emit = 0.0;
    amplitued = 10.0;
    speed = 1.0;
}

GDExample::~GDExample() {}

void GDExample::_process( double delta ) {
    time_passed += speed * delta;

    Vector2 new_position = Vector2(
        amplitued + ( amplitued * sin( time_passed * 2.0 ) ),
        amplitued + ( amplitued * cos( time_passed * 1.5 ) )
    );

    set_position( new_position );

    time_emit += delta;
    if ( time_emit > 1.0 ) {
        emit_signal( "position_changed", this, new_position );

        time_emit = 0.0;
    }
}

void GDExample::set_amplitued( const double p_amplitued ) {
    amplitued = p_amplitued;
}

double GDExample::get_amplitued() const {
    return amplitued;
}

void GDExample::set_speed( const double p_speed ) {
    speed = p_speed;
}

double GDExample::get_speed() const {
    return speed;
}
