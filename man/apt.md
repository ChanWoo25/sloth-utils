# Command `apt`

## apt install

> sudo apt install [options] pkg1[, pkg2, pkg3, ...]

Install or upgrade one or more packages. All packages required by the package(s) specified for installation will also be retrieved and installed. The `/etc/apt/sources.list` file is used to locate the desired packages. **A specific version** of a package can be selected for installation by following the package name with an equals (=) and the version of the package to select. Alternatively **a specific distribution** can be selected by following the package name with a slash and the version of the distribution or the Archive name (stable, testing, unstable).

### options

`y / --yes` \
**Usage**: sudo apt install -y <package> \
**Description**: Automatically answer "yes" to any prompts that come up during installation. This is useful when you want to install something without being asked for confirmation.

`f / --fix-broken` \
**Usage**: sudo apt install -f \
**Description**: Attempts to fix a broken installation. This is helpful when package dependencies are in a problematic state, and you want to resolve them by installing or removing packages.

`-no-install-recommends` \
**Usage**: sudo apt install --no-install-recommends <package> \
**Description**: Installs only the specified package, without any of the additional packages that are recommended by the system. This is useful for minimizing the number of packages installed.

`-reinstall` \
**Usage**: sudo apt install --reinstall <package> \
**Description**: Reinstalls the specified package even if it is already installed. This can be useful when you suspect the installation is corrupt or incomplete.

`-dry-run` \
**Usage**: sudo apt install --dry-run <package> \
**Description**: Shows what would happen if you were to run the install command, but doesn't actually install anything. This is useful for testing without making any changes to the system.

`d / --download-only` \
**Usage**: sudo apt install -d <package> \
**Description**: Downloads the specified package but doesn’t install it. This is useful if you want to download packages for offline installation later.

`-no-upgrade` \
**Usage**: sudo apt install --no-upgrade <package> \
**Description**: Installs the package only if it is not already installed. If the package is already installed, this option prevents it from being upgraded.

`-only-upgrade` \
**Usage**: sudo apt install --only-upgrade <package> \
**Description**: Upgrades the specified package to a newer version if it's already installed. It does not install the package if it’s not already present on the system.

`-auto-remove` \
**Usage**: sudo apt install --auto-remove \
**Description**: Removes packages that were automatically installed to satisfy dependencies for other packages and are no longer needed.

`--allow-downgrades` \
**Usage**: sudo apt install --allow-downgrades <package> \
**Description**: Allows you to downgrade a package if the version you are installing is older than the one currently installed. This is useful if you want to roll back to an earlier version of a package.

`--allow-remove-essential` \
**Usage**: sudo apt install --allow-remove-essential <package> \
**Description**: Permits the removal of essential system packages. This is potentially dangerous as it can cause system instability, so it should be used with caution.

`--allow-change-held-packages` \
**Usage**: sudo apt install --allow-change-held-packages <package> \
**Description**: Allows changes to packages that have been marked as "held," which means they are prevented from being upgraded, downgraded, or removed.

`-q / --quiet` \
**Usage**: sudo apt install -q <package> \
**Description**: Suppresses most of the output from the apt command. Useful for scripting where you want minimal output.

`--ignore-missing` \
**Usage**: sudo apt install --ignore-missing <package> \
**Description**: Installs packages but ignores any missing dependencies. This might result in incomplete installations if essential dependencies are not available.

`--allow-unauthenticated` \
**Usage**: sudo apt install --allow-unauthenticated <package> \
**Description**: Allows installation of packages from untrusted sources (without valid authentication keys). It’s generally not recommended as it can compromise security.

`--print-uris` \
**Usage**: sudo apt install --print-uris <package> \
**Description**: Prints the URIs of the packages that would be installed without actually downloading or installing them. This can be useful for seeing where packages are being fetched from.

`--ignore-hold` \
**Usage**: sudo apt install --ignore-hold <package> \
**Description**: Ignores any packages on hold and installs or upgrades them. Normally, held packages are not touched during installation or upgrade.