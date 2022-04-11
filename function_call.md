# Function Call

Comparison between:

- Direct
- Virtual Function
- Type Erasure
- Variant + Visit
- CRTP

## Test Machine Specification

- MacBook Pro 16" (2020)
- CPU: 8-Core Intel Core i9 (2.3 GHz)
- RAM: 16 GB
- macOS 12.3.1 (Monterey)

## Results

- Debug build by AppleClang 13.1.6.13160021

```
benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
direct call                                    100             1     18.856 ms
                                        185.791 us    181.465 us    194.006 us
                                         29.717 us    18.4219 us    46.3922 us

virtual function                               100             1    18.6759 ms
                                        187.252 us    184.162 us    192.632 us
                                        20.3371 us    13.1375 us    29.3869 us

type erasure                                   100             1    164.337 ms
                                        1.64622 ms    1.61806 ms    1.69172 ms
                                        181.166 us     129.49 us     307.18 us

variant + visit                                100             1    573.414 ms
                                        5.82184 ms    5.77561 ms    5.89234 ms
                                        285.799 us    205.103 us    418.577 us

CRTP                                           100             1    17.0187 ms
                                        172.704 us    169.577 us    177.993 us
                                        20.3391 us    13.9871 us    29.2004 us
```

- Release build by AppleClang 13.1.6.13160021

```
benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
direct call                                    100         82995          0 ns
                                       0.450099 ns   0.445806 ns   0.461361 ns
                                      0.0307026 ns 0.00152544 ns  0.0611303 ns

virtual function                               100             1    11.7458 ms
                                        113.188 us    111.847 us    116.512 us
                                        9.92923 us    3.42609 us    17.3238 us

type erasure                                   100             1    11.8622 ms
                                        116.178 us    112.094 us    123.972 us
                                        27.7664 us     16.805 us    43.0311 us

variant + visit                                100             1    12.6723 ms
                                        114.794 us    112.689 us     118.95 us
                                        14.4713 us    8.52474 us    23.2467 us

CRTP                                           100         83060          0 ns
                                       0.455694 ns   0.455673 ns   0.455717 ns
                                     0.000112578 ns 9.91414e-05 ns 0.00013122 ns
```

- Debug build by GCC 11.2.0

```
benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
direct call                                    100             1    17.4393 ms
                                        172.688 us    169.558 us    177.708 us
                                        19.7966 us    13.6759 us    27.4557 us

virtual function                               100             1    19.7908 ms
                                        197.218 us    191.018 us    208.188 us
                                         40.939 us    26.6496 us    65.1126 us

variant + visit                                100             1      568.8 ms
                                        5.70751 ms     5.6558 ms    5.77585 ms
                                        302.589 us    238.406 us    422.626 us

CRTP                                           100             1    21.3976 ms
                                        173.418 us    170.088 us    178.978 us
                                        21.5129 us    14.4569 us    30.8333 us
```

- Release build by GCC 11.2.0

```
benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
direct call                                    100        109822          0 ns
                                       0.218326 ns   0.218326 ns   0.218326 ns
                                     1.38778e-16 ns 1.38778e-16 ns 1.38778e-16 ns

virtual function                               100             1    12.1356 ms
                                        126.327 us    122.187 us    133.397 us
                                         26.962 us    18.2108 us    41.4733 us

type erasure                                   100             1    11.4529 ms
                                        116.027 us    112.017 us    123.737 us
                                        27.3596 us     16.468 us    41.8875 us

variant + visit                                100             1    11.4955 ms
                                        113.287 us    110.387 us    120.527 us
                                        21.7084 us    10.1729 us    43.1985 us

CRTP                                           100        107380          0 ns
                                       0.225806 ns   0.220032 ns   0.240147 ns
                                      0.0443476 ns  0.0205579 ns  0.0807034 ns
```
