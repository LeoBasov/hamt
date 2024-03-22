from setuptools import setup

setup(
    name='pyhamt',
    version='1.4.0',
    author='Leo Basov',
    licence='GNU General Public License v3.0',
    packages=['pyhamt'],
    package_data={'pyhamt': ['pyhamt*']},
    include_package_data=True,
    python_requires='>=3.6',
)
