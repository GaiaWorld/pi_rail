extern crate bindgen;

use std::env;
use std::path::PathBuf;

fn main() {
    // Tell cargo to tell rustc to link the system bzip2
    // shared library.
	// println!("cargo:rustc-link-search=rail/libs/win/Release_64");
    println!("cargo:rustc-link-lib=rail/libs/win/Release_64/rail_api64");
	
    // Tell cargo to invalidate the built crate whenever the wrapper changes
    println!("cargo:rerun-if-changed=wrapper.hpp");

    // The bindgen::Builder is the main entry point
    // to bindgen, and lets you build up options for
    // the resulting bindings.
    let bindings = bindgen::Builder::default()
        // The input header we would like to generate
        // bindings for.
		.header("wrapper.hpp")
		// .allowlist_recursively(true)
		.allowlist_function("NeedRestartAppForCheckingEnvironment")
		.allowlist_function("rail::RailInitialize")
		.allowlist_function("rail::RailFinalize")
		.allowlist_function("rail::RailRegisterEvent")
		.allowlist_function("rail::RailUnregisterEvent")
		.allowlist_function("rail::RailFireEvents")
		.allowlist_function("rail::RailFactory")
		.allowlist_function("CreateEventHandler")
		.allowlist_function("AsyncShowPaymentWindow")
		.allowlist_function("AsyncAcquireSessionTicket")

		.rustified_enum("rail::RAILEventID")
		.rustified_enum("rail::RailResult")
		.rustfmt_bindings(true)
        // Tell cargo to invalidate the built crate whenever any of the
        // included header files changed.
        .parse_callbacks(Box::new(bindgen::CargoCallbacks))
        // Finish the builder and generate the bindings.
        .generate()
        // Unwrap the Result and panic on failure.
        .expect("Unable to generate bindings");

    // Write the bindings to the $OUT_DIR/bindings.rs file.
    let out_path = PathBuf::from(env::var("OUT_DIR").unwrap());
    bindings
        .write_to_file(out_path.join("bindings.rs"))
        .expect("Couldn't write bindings!");
}