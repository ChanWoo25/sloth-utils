import apt
import apt.package

def print_installed_packages():
    cache = apt.Cache()
    installed_packages = [package for package in cache if package.is_installed]

    if installed_packages:
        print("Installed packages:")
        for package in installed_packages:
            print(type(package), package.name)
            print(package.fullname)
            print(package.shortname)
            print(package.versions)
            print(package.id)
            print(package.candidate)

    else:
        print("No installed packages found.")

def install_specific_version(package_name, version):
    cache = apt.Cache()

    if package_name in cache:
        package = cache[package_name]
        available_versions = [pkg.version for pkg in package.versions]

        if version in available_versions:
            package_version = package.versions[available_versions.index(version)]
            if not package_version.is_installed:
                package_version.mark_install()
        else:
            print(f"Version {version} not found for package {package_name}.")
            return

    # Apply the changes (install the marked packages)
    try:
        cache.commit()
    # except apt.cache.LockFailedException:
    #     print("Failed to acquire the APT lock.")
    # except apt.cache.FetchFailedException:
    #     print("Failed to fetch packages from APT repositories.")
    # except apt.package.VersionDivergenceException as e:
    #     print(f"Version divergence: {e}")
    except Exception as e:
        print(f"An error occurred: {e}")

import subprocess

def install_package_with_progress(package_name):
    # Redirect stdout and stderr to subprocess.PIPE to capture the output
    process = subprocess.Popen(
        ["sudo", "apt-get", "install", package_name],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        universal_newlines=True
    )

    # Print the output of the installation command line by line
    for line in process.stdout:
        print(line.strip())

    # Wait for the process to finish
    process.wait()


if __name__ == "__main__":
    # print_installed_packages()

    # package_name = "python3-minimal"
    # version_to_install = "3.10.6-1~22.04"
    # install_specific_version(package_name, version_to_install)

    # install_package_with_progress("python3-minimal")
    # install_package_with_progress("tree")
    # install_package_with_progress("htop")

    cli = "apt install python-dev"
    print(cli)
    print([*cli.split(), "abc"])

