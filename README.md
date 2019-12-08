# MiSTer-labs

This is a working fork of MiSTer-devel to add experimental features that may not be ready for prime-time.

## Mission Statement
* We do this for fun. 
* We want harmony in the community
* Goal is to test and refine features, to eventually contribute back to the main MiSTer project
* We need to make this fun for developers. Improvements to devops (e.g. reg testing, auto build) are welcome.
* These builds are for advanced users. Expect to see more options and more mess until a feature is refined.
* As much as possible, we will avoid making changes to the Linux stack of MiSTer
* For end users, use of mister-lab main and cores must be immediately revertable by change of files.

## Proposed Methodology
* 'master' is used to keep in sync with the main upstream repo. It represent the revision we last merged to.
* New features should be added to branches that are kept easy to merge
* 'labs-stable' will be used to collect features considered mature and mergable upstream (whenever that may be)
* 'labs-unstable' contains experimental builds with all the bleeding edge items
* Users are free to select whether they want the OG firmware, stable labs firmware, or wild-west labs firmware
* We should strive to keep delta with OG firmware minimal, and improve developer QoL to make it safer to try changes. 
  
