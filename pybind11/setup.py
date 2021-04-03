from setuptools import setup

setup(
    name='pyhamt',
    version='0.0.1',
    packages=['pyhamt'],
    package_data={'pyhamt': ['pyhamt*']},
    include_package_data=True,
    install_requires=[
        'importlib; python_version == "3.6"',
    ],
)
